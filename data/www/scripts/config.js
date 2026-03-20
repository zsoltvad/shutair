(() => {
  const fetchApplicationConfig = async () => {
    const response = await fetch('/application-config.json');
    window.shutAir.applicationConfig = await response.json();
  };

  window.shutAir = window.shutAir || {};
  window.shutAir.fetchApplicationConfig = fetchApplicationConfig;
})();
