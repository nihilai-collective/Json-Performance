
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3005.1 | 0.0324901 | 316.621ms | 9378 | 640 | 598.393 | 2976.13 | 0.0971375 | 1(Win) | true |
| Jsonifier (two-stage) | 2555.09 | 0.161243 | 395.835ms | 9378 | 4890 | 155767 | 3500.28 | 0.00848952 | 2(Loss) | true |
| Glaze | 1797.54 | 0.151425 | 514.339ms | 9378 | 4890 | 277567 | 4975.45 | 0.063172 | 3(Loss) | true |
| simdjson (ondemand) | 1764.96 | 0.0966138 | 524.127ms | 9378 | 2560 | 61358 | 5067.3 | 0.0374322 | 4(Loss) | true |
