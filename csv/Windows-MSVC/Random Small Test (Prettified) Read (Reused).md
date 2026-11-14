
----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1587.7 | 0.190646 | 584.917ms | 8051 | 320 | 27199.7 | 4835.94 | 0.187049 | 1.9054 | 1(Win) | true |
| Jsonifier | 1400.62 | 0.242604 | 646.468ms | 8051 | 320 | 56598.4 | 5481.88 | 0.0228076 | 2.16218 | 2(Loss) | true |
| Glaze | 1299.43 | 0.119645 | 687.226ms | 8051 | 4890 | 244396 | 5908.77 | 0.0491685 | 2.32982 | 3(Loss) | true |
| simdjson (ondemand) | 1076.86 | 0.175405 | 821.869ms | 8051 | 40 | 6256.41 | 7130 | 0.0935891 | 2.81339 | 4(Loss) | true |
