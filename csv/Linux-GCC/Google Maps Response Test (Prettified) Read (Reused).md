
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3372.55 | 0.0528384 | 776.934ms | 25388 | 30 | 431.679 | 7179.1 | 0.15484 | 0.73144 | 1(Win) | true |
| Jsonifier (two-stage) | 2941.1 | 0.0413741 | 868.552ms | 25388 | 40 | 464.038 | 8232.25 | 0.457272 | 0.839046 | 2(Loss) | true |
| simdjson (reflection) | 2898.93 | 0.132097 | 876.357ms | 25388 | 4890 | 595221 | 8352.01 | 0.0961443 | 0.851246 | 3(Loss) | true |
| simdjson (ondemand) | 2500.69 | 0.0608334 | 1011.45ms | 25388 | 80 | 2775.31 | 9682.08 | 0.06941 | 0.987299 | 4(Loss) | true |
| Glaze | 2396.95 | 0.384649 | 1041.44ms | 25388 | 640 | 966160 | 10101.1 | 0.399347 | 1.03014 | 5(Loss) | true |
