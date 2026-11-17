
----
### Apache Builds Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2351.76 | 0.0694082 | 824.642ms | 2632 | 1280 | 702.452 | 1067.32 | 0.200377 | 2.27862 | 9.46392 | 1.7747 | 0.00187031 | 5.93655e-05 | 1.42477e-05 | 1(Win) | true |
| simdjson (ondemand) | 1995.13 | 0.225474 | 843.681ms | 2632 | 30 | 241.403 | 1258.1 | 0.0132492 | 2.66554 | 10.1505 | 1.7196 | 0.00398936 | 7.59878e-05 | 1.26646e-05 | 2(Loss) | true |
