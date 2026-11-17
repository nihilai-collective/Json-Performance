
----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7703.55 | 0.0544506 | 308.809ms | 24579 | 80 | 219.605 | 3042.8 | 0.230582 | 0.318593 | 1(Win) | true |
| Glaze | 4160.28 | 0.235578 | 572.445ms | 24579 | 1280 | 225508 | 5634.33 | 0.126228 | 0.592394 | 2(Loss) | true |
| simdjson (reflection) | 551.982 | 0.0723688 | 4279.79ms | 24893 | 4890 | 4.73714e+06 | 43008.3 | 0.0877048 | 4.48266 | 3(Loss) | true |
