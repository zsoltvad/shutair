(() => {
  // CHANNEL GRID FACTORY

  const createChannelGrid = (channelCount, gridElementSelector) => {
    const channelGridElement = document.querySelector(gridElementSelector);

    for (let i = 1; i <= channelCount; i++) {
      const channelElement = document.createElement('div');
      channelElement.classList.add('channel');
      channelElement.setAttribute('data-id', i);
      channelElement.appendChild(createChannelIdentifier(i));
      channelElement.appendChild(createChannelActions(i));
      
      channelGridElement.append(channelElement);
    }
  };

  const createChannelIdentifier = (channel) => {
    const channelIdentifierElement = document.createElement('div');
    channelIdentifierElement.classList.add('channel__identifier');
    channelIdentifierElement.innerHTML = channel;

    return channelIdentifierElement;
  };

  const createChannelActions = (channel) => {
    const channelActionsElement = document.createElement('div');
    channelActionsElement.classList.add('channel__actions');

    channelActionsElement.appendChild(createChannelCommandButton(channel, 'up', '&uarr; '));
    channelActionsElement.appendChild(createChannelCommandButton(channel, 'stop', ''));
    channelActionsElement.appendChild(createChannelCommandButton(channel, 'down', '&darr; '));
    
    return channelActionsElement;
  };

  const createChannelCommandButton = (channel, command, prefix) => {
    let buttonElement = document.createElement('button');
    buttonElement.classList.add(`command-button`, `command-button--${command}`);
    buttonElement.innerHTML = `${prefix}${command}`;
    buttonElement.onclick = () => shutAir.fetchChannelCommand(channel, command);

    return buttonElement;
  };

  // FAVORITE GRID FACTORY

  const createFavoriteGrid = (favorites, gridElementSelector) => {
    const favoriteGridElement = document.querySelector(gridElementSelector);

    for (let i = 0; i < favorites.length; i++) {
      const favoriteElement = document.createElement('div');
      favoriteElement.classList.add('favorite');
      favoriteElement.setAttribute('data-id', i);
      favoriteElement.appendChild(createFavoriteIdentifier(favorites[i].name));
      favoriteElement.appendChild(createFavoriteActions(favorites[i].channels));
      
      favoriteGridElement.append(favoriteElement);
    }
  };

  const createFavoriteIdentifier = (name) => {
    const favoriteIdentifierElement = document.createElement('div');
    favoriteIdentifierElement.classList.add('favorite__identifier');
    favoriteIdentifierElement.innerHTML = name;

    return favoriteIdentifierElement;
  };

  const createFavoriteActions = (channels) => {
    const favoriteActionsElement = document.createElement('div');
    favoriteActionsElement.classList.add('favorite__actions');

    favoriteActionsElement.appendChild(createFavoriteCommandButton(channels, 'up', '&uarr; '));
    favoriteActionsElement.appendChild(createFavoriteCommandButton(channels, 'stop', ''));
    favoriteActionsElement.appendChild(createFavoriteCommandButton(channels, 'down', '&darr; '));
    
    return favoriteActionsElement;
  };

  const createFavoriteCommandButton = (channels, command, prefix) => {
    let buttonElement = document.createElement('button');
    buttonElement.classList.add(`command-button`, `command-button--${command}`);
    buttonElement.innerHTML = `${prefix}${command}`;
    buttonElement.onclick = () => {
      channels.forEach(channel => shutAir.fetchChannelCommand(channel, command));
    };

    return buttonElement;
  };

  window.shutAir = window.shutAir || {};
  window.shutAir.createChannelGrid = createChannelGrid;
  window.shutAir.createFavoriteGrid = createFavoriteGrid;
})();
