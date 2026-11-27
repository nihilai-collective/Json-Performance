
----
### Twitter Partial Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 4361.31 | 0.727299 | 5129.39ms | 466906 | 320 | 1.76441e+08 | 102097 | 0.046252 | 1(Win) | true |
| Jsonifier | 4210.58 | 0.227867 | 10299.5ms | 466906 | 4890 | 2.83953e+08 | 105752 | 0.28565 | 2(Loss) | true |
| simdjson (reflection) | 4018.03 | 0.130138 | 5736.86ms | 466906 | 640 | 1.33114e+07 | 110820 | 0.292861 | 3(Loss) | true |
| simdjson (ondemand) | 3495.06 | 0.759564 | 6607.73ms | 466906 | 80 | 7.4915e+07 | 127402 | 2.76444 | 4(Loss) | true |
| Glaze | 2543.98 | 0.110165 | 9247.28ms | 466906 | 320 | 1.18978e+07 | 175031 | 0.0718102 | 5(Loss) | true |
