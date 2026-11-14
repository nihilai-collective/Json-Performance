
----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8903.35 | 0.0407312 | 7510.31ms | 631514 | 1280 | 971681 | 67644.1 | 0.0629751 | 0.567061 | 2.72812 | 0.284768 | 0.000626382 | 4.4808e-06 | 2.88122e-06 | 1(Win) | true |
| Jsonifier | 8892.46 | 0.0246553 | 7514.53ms | 631514 | 4890 | 1.36349e+06 | 67726.9 | 0.0108932 | 0.567723 | 2.73018 | 0.285305 | 0.000639179 | 2.80075e-06 | 1.48052e-06 | 2(Loss) | true |
| simdjson (reflection) | 8406.38 | 0.0551086 | 7925.58ms | 631514 | 640 | 997623 | 71643 | 0.0303976 | 0.600955 | 3.00764 | 0.2896 | 0.000718432 | 1.27669e-05 | 2.25401e-06 | 3(Loss) | true |
| simdjson (ondemand) | 8172.18 | 0.0178494 | 8116.48ms | 631514 | 4890 | 846149 | 73696.2 | 0.0325638 | 0.617909 | 3.03105 | 0.290151 | 0.000569002 | 1.52385e-05 | 3.42897e-06 | 4(Loss) | true |
| Glaze | 3818.83 | 0.0810722 | 8408.39ms | 631514 | 320 | 5.23118e+06 | 157708 | 0.08009 | 1.3209 | 5.85695 | 0.962476 | 0.00136849 | 1.59834e-06 | 6.13605e-07 | 5(Loss) | true |
