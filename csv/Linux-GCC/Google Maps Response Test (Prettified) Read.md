
----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2672.05 | 0.0380278 | 1634.19ms | 25388 | 1280 | 15197.7 | 9061.16 | 0.155153 | 1.93489 | 9.08707 | 1.59997 | 0.00261682 | 1.16627e-05 | 4.1235e-06 | 1(Win) | true |
| simdjson (ondemand) | 2205.41 | 0.0234391 | 1821ms | 25388 | 4890 | 32379.3 | 10978.4 | 0.00983189 | 2.34185 | 9.81304 | 1.72733 | 0.00229709 | 9.84314e-06 | 2.76285e-06 | 2(Loss) | true |
