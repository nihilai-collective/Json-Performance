
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3615.88 | 0.305426 | 570.613ms | 18245 | 1280 | 276492 | 4812.05 | 0.36361 | 0.680844 | 1(Win) | true |
| Jsonifier | 2924.83 | 0.0597713 | 711.844ms | 18245 | 30 | 379.31 | 5949 | 0.0504541 | 0.842717 | 2(Loss) | true |
| simdjson (ondemand) | 2095.8 | 0.399444 | 958.811ms | 18245 | 320 | 351923 | 8302.2 | 0.0423278 | 1.17713 | 3(Loss) | true |
| Glaze | 1961.56 | 0.152081 | 962.728ms | 18245 | 2560 | 465876 | 8870.36 | 0.490306 | 1.25838 | 4(Loss) | true |
