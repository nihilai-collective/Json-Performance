
----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1988.59 | 0.262633 | 3138.88ms | 65103 | 320 | 2.15161e+06 | 31221.7 | 0.345229 | 1.24386 | 1(Win) | true |
| Jsonifier | 1967.28 | 0.182286 | 3200.23ms | 65103 | 640 | 2.11815e+06 | 31559.8 | 0.058326 | 1.25734 | 2(Loss) | true |
| Jsonifier (two-stage) | 1795.28 | 0.0754693 | 3513.55ms | 65103 | 4890 | 3.33109e+06 | 34583.4 | 1.05686 | 1.37787 | 3(Loss) | true |
| Glaze | 1500.83 | 0.0810176 | 4118.43ms | 65103 | 4890 | 5.49296e+06 | 41368.4 | 0.235411 | 1.64849 | 4(Loss) | true |
| simdjson (ondemand) | 1491.22 | 0.134616 | 4186.38ms | 65103 | 2560 | 8.04175e+06 | 41635 | 0.09636 | 1.65909 | 5(Loss) | true |
