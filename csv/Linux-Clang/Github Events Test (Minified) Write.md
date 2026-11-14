
----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16545.8 | 0.182491 | 1081.96ms | 58581 | 4890 | 185665 | 3376.53 | 0.0141679 | 0.308571 | 1.077 | 0.164456 | 4.54093e-05 | 2.29769e-05 | 1.27731e-05 | 1(Win) | true |
| Glaze | 5335.59 | 0.174519 | 1805.02ms | 58581 | 2560 | 854823 | 10470.7 | 0.067673 | 0.958129 | 2.62659 | 0.382599 | 8.01441e-05 | 6.55476e-05 | 4.21225e-05 | 2(Loss) | true |
