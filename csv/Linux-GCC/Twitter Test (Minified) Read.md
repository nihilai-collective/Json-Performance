
----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2270.6 | 0.073744 | 5199.42ms | 466906 | 1280 | 2.67696e+07 | 196105 | 0.100485 | 2.19722 | 6.62104 | 1.2012 | 0.0104029 | 0.0140528 | 6.57788e-05 | 1(Win) | true |
| Glaze | 1726 | 0.146685 | 6818.85ms | 466906 | 640 | 9.16497e+07 | 257981 | 0.0409806 | 2.91551 | 10.4305 | 1.87129 | 0.0130369 | 0.0170376 | 7.26023e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1634.85 | 0.215947 | 7165.57ms | 466906 | 320 | 1.10701e+08 | 272366 | 0.137459 | 3.07707 | 9.39713 | 1.49232 | 0.020977 | 0.028194 | 0.00019919 | 3(Loss) | true |
| simdjson (reflection) | 1587.43 | 0.169232 | 7386.61ms | 466906 | 640 | 1.44216e+08 | 280501 | 0.191224 | 3.15912 | 10.0994 | 1.51196 | 0.0133674 | 0.0266209 | 0.000226193 | 4(Loss) | true |
| simdjson (ondemand) | 1148.78 | 0.132152 | 5054.53ms | 466906 | 640 | 1.67924e+08 | 387607 | 0.320167 | 4.3799 | 13.1012 | 2.73535 | 0.0137849 | 0.0465015 | 0.000120835 | 5(Loss) | true |
