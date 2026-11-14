
----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1408.78 | 0.120981 | 7634.04ms | 7351818 | 80 | 2.90023e+09 | 4.97683e+06 | 2.3669 | 1.75742 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 868.196 | 0.254793 | 5842.78ms | 7351818 | 40 | 1.69351e+10 | 8.07564e+06 | 9.40489 | 2.85158 | -(Loss) | false |
