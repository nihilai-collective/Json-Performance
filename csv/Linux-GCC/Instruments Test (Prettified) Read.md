
----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3649.42 | 0.0486428 | 4836ms | 183677 | 4890 | 2.66568e+06 | 47998.9 | 0.0666023 | 0.677995 | 1(Win) | true |
| Jsonifier | 2814.52 | 0.151222 | 6278.71ms | 183677 | 640 | 5.66906e+06 | 62237.3 | 0.628424 | 0.879254 | 2(Loss) | true |
| simdjson (reflection) | 2536.96 | 0.128692 | 6868.7ms | 183677 | 640 | 5.05322e+06 | 69046.5 | 0.154743 | 0.975531 | 3(Loss) | true |
| Glaze | 2317.03 | 0.216262 | 7765.46ms | 183677 | 320 | 8.55376e+06 | 75600.4 | 0.342266 | 1.06817 | 4(Loss) | true |
| simdjson (ondemand) | 1748.68 | 0.309541 | 5170.13ms | 183677 | 80 | 7.69156e+06 | 100172 | 0.400136 | 1.41546 | 5(Loss) | true |
