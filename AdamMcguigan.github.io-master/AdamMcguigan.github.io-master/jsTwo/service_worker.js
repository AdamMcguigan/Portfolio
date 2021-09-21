var cacheName = 'AdamMcguigans-pwa';
var filesToCache = [
  '/',
  '/index.html',
  '/UI-Project.html',
  '/cssTwo/push/push.css',
  '/jsTwo/scriptTwo.js'
];

/* Cache contents when Offline See Cache */
self.addEventListener('install', function(e) {
  e.waitUntil(
    caches.open(cacheName).then(function(cache) {
      return cache.addAll(filesToCache);
    })
  );
});

/* Serve cached content when offline, examine Cache Storage */
self.addEventListener('fetch', function(e) {
  e.respondWith(
    caches.match(e.request).then(function(response) {
      return response || fetch(e.request);
    })
  );
});