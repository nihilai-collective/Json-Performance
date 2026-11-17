
----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2494.05 | 0.0906653 | 1437.24ms | 18245 | 320 | 12803 | 6976.52 | 0.0854816 | 2.03803 | 8.02017 | 1.46435 | 0.00145262 | 3.78528e-05 | 2.41505e-05 | 1(Win) | true |
| simdjson (reflection) | 2291.8 | 0.0584928 | 1509.4ms | 18245 | 1280 | 25243.4 | 7592.19 | 0.0365847 | 2.21868 | 8.31576 | 1.42806 | 0.00142171 | 2.4964e-05 | 1.31029e-05 | 2(Loss) | true |
| Jsonifier | 2174.76 | 0.0303545 | 1542.02ms | 18245 | 4890 | 28841.7 | 8000.8 | 0.102621 | 2.33831 | 8.27947 | 1.91072 | 0.00183945 | 5.95059e-05 | 3.30426e-05 | 3(Loss) | true |
| Glaze | 1796.89 | 0.0665509 | 1701.63ms | 18245 | 320 | 13289.3 | 9683.26 | 0.0305524 | 2.82371 | 12.1423 | 2.39156 | 0.00371215 | 1.76418e-05 | 4.96711e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1794 | 0.0210633 | 1714.48ms | 18245 | 4890 | 20408.3 | 9698.89 | 0.0350802 | 2.82669 | 10.3359 | 1.92201 | 0.00196414 | 2.0859e-05 | 7.95803e-06 | 5(Loss) | true |
