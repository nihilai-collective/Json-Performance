
----
### Google Maps Response Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2350.27 | 0.0354731 | 1200.65ms | 11812 | 1280 | 3700.16 | 4792.98 | 0.110294 | 2.20961 | 10.5319 | 1.9415 | 0.00349916 | 1.29635e-05 | 1.32281e-07 | 1(Win) | true |
| simdjson (ondemand) | 2061.1 | 0.0192324 | 1267.79ms | 11812 | 4890 | 5402.88 | 5465.44 | 0.0254538 | 2.51445 | 11.7105 | 1.87868 | 0.00363019 | 2.44111e-05 | 9.48742e-06 | 2(Loss) | true |
