
----
### Canada Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5991.04 | 0.048496 | 8713.21ms | 2090234 | 1280 | 3.33278e+07 | 332731 | 0.151124 | 0.850025 | 4.69133 | 0.718822 | 0.0026089 | 0.076328 | 1.91889e-06 | 1(Win) | true |
| simdjson (ondemand) | 5538.54 | 0.0821172 | 9404.22ms | 2090234 | 640 | 5.59047e+07 | 359915 | 0.0502704 | 0.921028 | 5.09755 | 0.738335 | 0.00243247 | 0.075888 | 8.41712e-07 | 2(Loss) | true |
