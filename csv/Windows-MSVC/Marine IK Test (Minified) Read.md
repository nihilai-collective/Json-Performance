
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 231.264 | 1.32926 | 5299.11ms | 1834197 | 40 | 4.04349e+11 | 7.56376e+06 | 0.75907 | 10.7056 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 222.292 | 0.610839 | 5575.31ms | 1834197 | 40 | 9.24186e+10 | 7.86906e+06 | 3.24372 | 11.1378 | -(Loss) | false |
