
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11399.3 | 0.0755344 | 5451.06ms | 631514 | 2560 | 4.07701e+06 | 52833.1 | 0.328818 | 0.21707 | 1(Win) | true |
| Jsonifier (two-stage) | 11323 | 0.0581425 | 5409.65ms | 631514 | 4890 | 4.67673e+06 | 53189.2 | 0.37909 | 0.218537 | 2(Loss) | true |
| simdjson (ondemand) | 9388.37 | 0.0438292 | 6481.08ms | 631514 | 4890 | 3.86564e+06 | 64149.4 | 0.00122056 | 0.263579 | 3(Loss) | true |
| Glaze | 4221.74 | 0.15832 | 7412.01ms | 631514 | 80 | 4.08079e+06 | 142656 | 0.0676294 | 0.586339 | 4(Loss) | true |
