
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1331.01 | 0.0955695 | 4785.7ms | 65103 | 2560 | 5.0877e+06 | 46646.8 | 0.0201756 | 1.85897 | 1(Win) | true |
| simdjson (ondemand) | 1196.36 | 0.152686 | 5247.87ms | 65103 | 640 | 4.01846e+06 | 51896.8 | 0.143799 | 2.06833 | 2(Loss) | true |
