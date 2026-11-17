
----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15509.8 | 0.230664 | 75.3987ms | 11812 | 40 | 112.267 | 726.3 | 0.110026 | 0.154125 | 1(Win) | true |
| simdjson (reflection) | 12054.4 | 0.0320888 | 98.3599ms | 11812 | 640 | 57.5493 | 934.494 | 0.0872038 | 0.199636 | 2(Loss) | true |
| Glaze | 3729.5 | 0.2882 | 303.965ms | 11812 | 1280 | 96993.6 | 3020.46 | 0.412383 | 0.65789 | 3(Loss) | true |
