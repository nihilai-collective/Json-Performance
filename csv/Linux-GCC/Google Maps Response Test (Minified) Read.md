
----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2504.73 | 0.0314693 | 1178.75ms | 11812 | 4890 | 9795.09 | 4497.42 | 0.129486 | 2.05303 | 10.1043 | 1.61179 | 0.00260961 | 2.82891e-05 | 1.06301e-05 | 1(Win) | true |
| Glaze | 1924.3 | 0.0616957 | 1306.73ms | 11812 | 1280 | 16696.3 | 5853.97 | 0.14652 | 2.65001 | 13.1048 | 2.62318 | 0.00150992 | 3.80307e-05 | 1.26328e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1772.03 | 0.0528602 | 1372.32ms | 11812 | 2560 | 28906.8 | 6356.99 | 0.109251 | 2.87085 | 13.5533 | 2.14397 | 0.0063971 | 2.3546e-05 | 7.50693e-06 | 3(Loss) | true |
| simdjson (reflection) | 1498.29 | 0.0917395 | 1485.96ms | 11812 | 640 | 30447.4 | 7518.45 | 0.0922125 | 3.39006 | 13.4807 | 2.15205 | 0.00408007 | 2.48688e-05 | 1.0847e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1103.69 | 0.0332111 | 1759.8ms | 11812 | 4890 | 56185.7 | 10206.4 | 0.120312 | 4.60484 | 17.7471 | 3.19638 | 0.00844762 | 7.19174e-05 | 4.06678e-05 | 5(Loss) | true |
