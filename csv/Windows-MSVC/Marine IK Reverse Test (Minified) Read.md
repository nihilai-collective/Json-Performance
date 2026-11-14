
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 175.892 | 1.61446 | 7060.37ms | 1834197 | 40 | 1.03113e+12 | 9.94491e+06 | 0.916177 | 14.0757 | 1(Win) | true |
| simdjson (ondemand) | 123.441 | 1.28317 | 9923.05ms | 1834197 | 40 | 1.32251e+12 | 1.41705e+07 | 0.572802 | 20.0564 | 2(Loss) | true |
