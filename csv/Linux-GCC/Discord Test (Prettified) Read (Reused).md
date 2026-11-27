
----
### Discord Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3242.79 | 0.303803 | 2853.59ms | 83958 | 160 | 900310 | 24691.3 | 0.152056 | 0.762636 | 1(Win) | true |
| Jsonifier (two-stage) | 3083.2 | 0.285023 | 2941.87ms | 83958 | 4890 | 2.6791e+07 | 25969.3 | 0.125913 | 0.802127 | 2(Loss) | true |
| simdjson (reflection) | 2653.82 | 0.144006 | 3366.67ms | 83958 | 640 | 1.20815e+06 | 30171.1 | 0.482741 | 0.932073 | 3(Loss) | true |
| simdjson (ondemand) | 2468.46 | 0.17096 | 3623ms | 83958 | 320 | 984033 | 32436.7 | 0.0526326 | 1.00212 | 4(Loss) | true |
| Glaze | 2168.52 | 0.154796 | 4040.89ms | 83958 | 320 | 1.04537e+06 | 36923.2 | 0.0382827 | 1.14085 | 5(Loss) | true |
