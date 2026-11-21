
----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1972.15 | 0.134049 | 566.616ms | 11579 | 4890 | 275485 | 5599.27 | 0.169096 | 1.2495 | 1(Win) | true |
| Jsonifier | 1828.28 | 0.38229 | 610.368ms | 11579 | 320 | 170605 | 6039.88 | 0.145081 | 1.34838 | 2(Loss) | true |
| simdjson (ondemand) | 1773.16 | 0.29056 | 625.241ms | 11579 | 1280 | 419109 | 6227.63 | 0.0442513 | 1.38986 | 3(Loss) | true |
| Glaze | 1644.16 | 0.55894 | 671.779ms | 11579 | 320 | 450955 | 6716.24 | 0.0128869 | 1.49991 | 4(Loss) | true |
