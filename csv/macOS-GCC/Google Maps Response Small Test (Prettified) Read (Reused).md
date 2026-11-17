
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2606.23 | 0.264115 | 395.31ms | 9378 | 4890 | 401689 | 3431.6 | 2.16148 | 1(Win) | true |
| Jsonifier (two-stage) | 2494.87 | 0.239354 | 416.637ms | 9378 | 4890 | 360012 | 3584.79 | 1.44107 | 2(Loss) | true |
| simdjson (reflection) | 1949.46 | 0.264537 | 499.804ms | 9378 | 2560 | 377054 | 4587.7 | 1.58107 | 3(Loss) | true |
| Glaze | 1750.62 | 0.524477 | 591.02ms | 9378 | 160 | 114871 | 5108.8 | 0.343321 | 4(Loss) | true |
| simdjson (ondemand) | 1494.4 | 0.187611 | 656.147ms | 9378 | 2560 | 322730 | 5984.7 | 0.705137 | 5(Loss) | true |
