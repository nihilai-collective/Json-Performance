
----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2268.59 | 0.0388719 | 2329.5ms | 56369 | 40 | 3393.9 | 23696.5 | 0.606065 | 1.09006 | 1(Win) | true |
| Jsonifier (two-stage) | 1931.62 | 0.830892 | 2799.6ms | 56369 | 80 | 4.27776e+06 | 27830.4 | 0.888493 | 1.28049 | 2(Loss) | true |
| Glaze | 1493.75 | 0.193909 | 3602.1ms | 56369 | 640 | 3.11675e+06 | 35988.4 | 0.0015543 | 1.65613 | 3(Loss) | true |
| simdjson (ondemand) | 828.31 | 0.0481756 | 6601.91ms | 56369 | 4890 | 4.78033e+06 | 64900.4 | 0.0766493 | 2.98778 | 4(Loss) | true |
