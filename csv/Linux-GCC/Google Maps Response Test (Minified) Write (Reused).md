
----
### Google Maps Response Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14838.9 | 0.141819 | 80.5345ms | 11812 | 320 | 370.905 | 759.141 | 0.319221 | 0.161134 | 1(Win) | true |
| simdjson (reflection) | 11745.2 | 0.110925 | 99.7208ms | 11812 | 30 | 33.9552 | 959.1 | 0.069558 | 0.204992 | 2(Loss) | true |
| Glaze | 4274.42 | 0.0802958 | 265.693ms | 11812 | 40 | 179.118 | 2635.4 | 0.0151803 | 0.573557 | 3(Loss) | true |
