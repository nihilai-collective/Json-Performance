
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2592.76 | 0.0833168 | 8484.63ms | 7351818 | 30 | 1.52283e+08 | 2.70416e+06 | 0.0868327 | 0.95489 | 1(Win) | true |
| Jsonifier | 2535.84 | 0.183855 | 8746.8ms | 7351818 | 30 | 7.75213e+08 | 2.76486e+06 | 0.149625 | 0.976305 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 2190.37 | 0.0480381 | 10153.7ms | 7351818 | 80 | 1.89154e+08 | 3.20094e+06 | 2.64022 | 1.13031 | -(Loss) | false |
| Glaze | 1998.01 | 0.443652 | 5245.26ms | 7351818 | 30 | 7.27114e+09 | 3.50912e+06 | 1.11323 | 1.23914 | 4(Loss) | true |
| simdjson (ondemand) | 1969.52 | 0.0854226 | 5315.97ms | 7351818 | 30 | 2.77418e+08 | 3.55987e+06 | 0.559998 | 1.25706 | 5(Loss) | true |
