
----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7739.35 | 0.0501644 | 50.5119ms | 3808 | 640 | 35.4615 | 469.238 | 0.0546397 | 0.300991 | 1(Win) | true |
| simdjson (ondemand) | 7709.06 | 0.106272 | 50.4787ms | 3808 | 160 | 40.1003 | 471.081 | 0.00928628 | 0.301224 | 2(Loss) | true |
| Jsonifier (two-stage) | 7569.97 | 0.319518 | 50.8758ms | 3808 | 4890 | 11489.6 | 479.737 | 0.371388 | 0.30872 | 3(Loss) | true |
| Glaze | 3828.52 | 0.0850545 | 99.157ms | 3808 | 160 | 104.147 | 948.562 | 0.0013178 | 0.628422 | 4(Loss) | true |
