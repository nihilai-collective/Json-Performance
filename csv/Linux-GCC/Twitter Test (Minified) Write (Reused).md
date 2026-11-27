
----
### Twitter Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12996.8 | 0.203023 | 3517.24ms | 475954 | 640 | 3.21754e+06 | 34924.3 | 0.166155 | 0.190303 | 1(Win) | true |
| simdjson (reflection) | 10219.1 | 0.149132 | 4492.02ms | 475954 | 1280 | 5.61642e+06 | 44417.3 | 0.212769 | 0.242104 | 2(Loss) | true |
| Glaze | 6517.52 | 0.479622 | 7273.17ms | 475954 | 30 | 3.34722e+06 | 69643.8 | 0.37289 | 0.379711 | 3(Loss) | true |
