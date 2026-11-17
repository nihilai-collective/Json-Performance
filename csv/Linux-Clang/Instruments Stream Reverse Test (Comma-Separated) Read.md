
----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 989.046 | 0.0424069 | 6276.49ms | 4197495 | 80 | 2.35673e+08 | 4.04738e+06 | 0.0191038 | 5.10691 | 27.8269 | 5.76686 | 0.00117435 | 0.0845791 | 0.00243011 | 1(Win) | true |
| simdjson (ondemand) | 626.147 | 0.133065 | 9832.31ms | 4197495 | 30 | 2.1711e+09 | 6.39313e+06 | 0.259785 | 8.08199 | 39.6264 | 6.40632 | 0.0151085 | 0.104148 | 0.00956223 | 2(Loss) | true |
