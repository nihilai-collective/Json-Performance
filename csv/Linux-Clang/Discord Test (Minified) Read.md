
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1414.94 | 0.123425 | 3731.4ms | 56369 | 640 | 1.40732e+06 | 37993 | 0.0449956 | 1.74851 | 1(Win) | true |
| simdjson (ondemand) | 1270.7 | 0.0702456 | 4279.46ms | 56369 | 2560 | 2.26086e+06 | 42305.5 | 0.400367 | 1.94716 | 2(Loss) | true |
