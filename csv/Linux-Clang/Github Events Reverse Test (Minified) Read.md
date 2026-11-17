
----
### Github Events Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 970.788 | 0.0255941 | 5970.91ms | 53331 | 2560 | 460288 | 52390.9 | 0.011186 | 5.30546 | 19.4979 | 3.91727 | 0.0165437 | 1.82601e-05 | 5.30297e-06 | 1(Win) | true |
| simdjson (ondemand) | 439.577 | 0.105538 | 6324.24ms | 53331 | 640 | 9.54304e+06 | 115703 | 0.0973844 | 11.6173 | 40.8149 | 7.37027 | 0.068995 | 3.50113e-05 | 1.79012e-05 | 2(Loss) | true |
