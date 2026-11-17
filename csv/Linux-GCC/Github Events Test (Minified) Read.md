
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1671.37 | 0.0410762 | 3784.1ms | 53331 | 2560 | 399977 | 30430.4 | 0.0183146 | 3.02623 | 9.88145 | 1.7251 | 0.010564 | 0.000125484 | 7.64975e-05 | 1(Win) | true |
| simdjson (reflection) | 1565.35 | 0.0674343 | 4003.49ms | 53331 | 2560 | 1.22897e+06 | 32491.5 | 0.109965 | 3.22947 | 10.8558 | 1.89891 | 0.0104767 | 0.000160114 | 7.5765e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1533.46 | 0.0696029 | 4060.9ms | 53331 | 1280 | 682152 | 33167.2 | 0.11522 | 3.27733 | 10.6979 | 1.80513 | 0.0105931 | 0.000133131 | 5.86256e-05 | 3(Loss) | true |
| Glaze | 1475.3 | 0.065636 | 4183.9ms | 53331 | 2560 | 1.31077e+06 | 34474.7 | 0.0475983 | 3.4305 | 11.6365 | 2.27582 | 0.0190522 | 0.000124971 | 7.17732e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1423.47 | 0.0745552 | 4331.4ms | 53331 | 640 | 454149 | 35729.8 | 0.100722 | 3.54608 | 11.1027 | 2.05146 | 0.00484794 | 0.000151178 | 7.79331e-05 | 5(Loss) | true |
