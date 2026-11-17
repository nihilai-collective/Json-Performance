
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1650.71 | 0.249268 | 3588.48ms | 56369 | 320 | 2.10875e+06 | 32566.4 | 0.07733 | 1.49858 | 1(Win) | true |
| simdjson (ondemand) | 1575.47 | 0.108688 | 3864.94ms | 56369 | 1280 | 1.76048e+06 | 34121.6 | 0.186832 | 1.57024 | 2(Loss) | true |
