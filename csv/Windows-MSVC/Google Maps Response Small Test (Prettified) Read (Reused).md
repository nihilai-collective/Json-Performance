
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2371.83 | 0.113862 | 430.167ms | 9378 | 2560 | 47189.8 | 3770.74 | 0.225305 | 1.27498 | 1(Win) | true |
| Jsonifier (two-stage) | 2274.76 | 0.114144 | 444.625ms | 9378 | 2560 | 51558.1 | 3931.64 | 0.097462 | 1.32937 | 2(Loss) | true |
| Glaze | 1675.46 | 0.27628 | 594.559ms | 9378 | 640 | 139198 | 5337.97 | 0.0849593 | 1.80625 | 3(Loss) | true |
| simdjson (ondemand) | 1381.7 | 0.0774923 | 717.26ms | 9378 | 2560 | 64409.2 | 6472.85 | 0.128377 | 2.19308 | 4(Loss) | true |
