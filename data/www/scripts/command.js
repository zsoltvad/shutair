(() => {
  const showAuthenticationForm = (authenticationElementSelector) => {
    const authenticationElement = document.querySelector(authenticationElementSelector);
    authenticationElement.style.display = 'flex';
    
    const bodyElement = document.querySelector('body');
    bodyElement.style.overflow = 'hidden';

    const inputElement = document.querySelector(`${authenticationElementSelector} input`);
    inputElement.addEventListener('input', async (event) => {
      const value = event.target.value;

      if (value.length < 4) {
        return;
      }

      const isAuthenticated = await fetchAuthentication(value);

      if (isAuthenticated) {
        localStorage.setItem('pin', value);
        authenticationElement.style.display = 'none';
        bodyElement.style.overflow = 'inherit';
        
        // remove all event listeners
        const clonedInputElement = inputElement.cloneNode(true);
        inputElement.parentNode.replaceChild(clonedInputElement, inputElement);
      }
    });
  }
  
  const authenticate = (authenticationElementSelector) => {
    if (localStorage.getItem('pin') !== null) {
      return;
    }

    showAuthenticationForm(authenticationElementSelector);
  };

  const fetchAuthentication = async (pin) => {
    const fetchOptions = {
      headers: new Headers({
        'Authorization': pin
      })
    };
    const response = await fetch('/authenticate', fetchOptions);
    
    if (response.status === 204) {
      console.log('Authenticated');
      return true;
    }

    return false;
  };

  const fetchChannelCommand = async (id, command) => {
    const fetchOptions = {
      headers: new Headers({
        'Authorization': localStorage.getItem('pin')
      })
    };
    const response = await fetch(`/${command}?id=${id}`, fetchOptions);
    
    if (response.status === 204) {
      console.log('Channel command executed: ', `{ ID: ${id}, Command: ${command} }`);
    }
  };

  window.shutAir = window.shutAir || {};
  window.shutAir.authenticate = authenticate;
  window.shutAir.fetchChannelCommand = fetchChannelCommand;
})();
