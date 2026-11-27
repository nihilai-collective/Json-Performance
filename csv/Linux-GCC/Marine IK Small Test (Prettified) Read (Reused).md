
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3166.45 | 0.0762732 | 638.389ms | 18245 | 40 | 702.664 | 5495.05 | 0.324389 | 0.777895 | 1(Win) | true |
| Jsonifier | 2807.55 | 0.220767 | 684.897ms | 18245 | 2560 | 479227 | 6197.49 | 0.117833 | 0.877774 | 2(Loss) | true |
| simdjson (reflection) | 2502.27 | 0.12077 | 758.568ms | 18245 | 80 | 5641.96 | 6953.61 | 0.396867 | 0.985503 | 3(Loss) | true |
| Glaze | 1898.17 | 0.0868069 | 995.484ms | 18245 | 4890 | 309623 | 9166.59 | 0.139169 | 1.30043 | 4(Loss) | true |
| simdjson (ondemand) | 1807.08 | 0.741081 | 1008.99ms | 18245 | 80 | 407339 | 9628.69 | 0.15746 | 1.3661 | 5(Loss) | true |
