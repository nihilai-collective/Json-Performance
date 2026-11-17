
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1298.02 | 0.906843 | 723.537ms | 9578 | 80 | 325791 | 7037.07 | 0.440681 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 1079.56 | 0.49882 | 861.171ms | 9578 | 1280 | 2.28008e+06 | 8461.09 | 5.33327 | -(Loss) | false |
| simdjson (ondemand) | 782.08 | 0.3062 | 1157.73ms | 9578 | 2560 | 3.27414e+06 | 11679.5 | 1.26158 | 3(Loss) | true |
| Jsonifier (two-stage) | 611.57 | 0.420173 | 1475.25ms | 9578 | 2560 | 1.00822e+07 | 14935.8 | 0.226812 | 4(Loss) | true |
