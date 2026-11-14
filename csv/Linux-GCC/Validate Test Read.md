
----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2987.25 | 0.172631 | 5335.06ms | 631514 | 160 | 1.93813e+07 | 201610 | 0.0129692 | 1.69651 | 8.25722 | 1.35256 | 0.00540275 | 9.17438e-06 | 4.93853e-06 | 1(Win) | true |
| Glaze | 2171.5 | 0.0606996 | 7258.97ms | 631514 | 1280 | 3.62766e+07 | 277347 | 0.449344 | 2.32337 | 9.80782 | 1.64384 | 0.00964837 | 1.15682e-05 | 9.66056e-06 | 2(Loss) | true |
