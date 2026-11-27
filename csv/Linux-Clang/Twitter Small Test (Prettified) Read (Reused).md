
----
### Twitter Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3324.64 | 0.0574576 | 116.878ms | 3808 | 160 | 63.0258 | 1092.33 | 0.0286005 | 0.727015 | 1(Win) | true |
| Jsonifier (two-stage) | 2852.98 | 0.22182 | 134.304ms | 3808 | 4890 | 38985.9 | 1272.91 | 0.129596 | 0.84927 | 2(Loss) | true |
| Glaze | 2479.24 | 0.0315865 | 155.381ms | 3808 | 320 | 68.5034 | 1464.8 | 0.0211161 | 0.980957 | 3(Loss) | true |
| simdjson (ondemand) | 1403.48 | 0.0506336 | 270.667ms | 3808 | 160 | 274.65 | 2587.56 | 0.0748214 | 1.74467 | 4(Loss) | true |
