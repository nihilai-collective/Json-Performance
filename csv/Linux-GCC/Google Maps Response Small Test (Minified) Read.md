
----
### Google Maps Response Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2408.87 | 0.0732094 | 893.138ms | 4390 | 2560 | 4144.55 | 1738.01 | 0.169662 | 2.18055 | 10.3087 | 1.69499 | 0.0011499 | 2.7406e-05 | 6.94049e-06 | 1(Win) | true |
| Glaze | 1835.29 | 0.0639587 | 947.513ms | 4390 | 4890 | 10409.4 | 2281.18 | 0.0578844 | 2.8407 | 13.1419 | 2.61298 | 0.0006005 | 6.57751e-05 | 3.35397e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1596.56 | 0.0617022 | 984.936ms | 4390 | 160 | 418.873 | 2622.29 | 0.108566 | 3.27782 | 15.3175 | 2.40501 | 0.00395644 | 5.9795e-05 | 2.2779e-05 | 3(Loss) | true |
| simdjson (reflection) | 1532.27 | 0.0484276 | 995.128ms | 4390 | 2560 | 4482.12 | 2732.3 | 0.293786 | 3.41357 | 13.2278 | 2.12187 | 0.00196736 | 3.6838e-05 | 7.11845e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1193.08 | 0.0916637 | 1072.41ms | 4390 | 1280 | 13243.3 | 3509.1 | 0.135546 | 4.3638 | 17.3731 | 3.07722 | 0.0019259 | 6.83371e-05 | 2.11774e-05 | 5(Loss) | true |
