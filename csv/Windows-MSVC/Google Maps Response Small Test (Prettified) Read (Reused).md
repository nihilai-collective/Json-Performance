
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2337.04 | 0.255366 | 435.029ms | 9378 | 320 | 30560.7 | 3826.88 | 0.0163292 | 1.29306 | 1(Win) | true |
| Jsonifier | 2182.24 | 0.078406 | 464.078ms | 9378 | 4890 | 50492.2 | 4098.34 | 0.199214 | 1.38646 | 2(Loss) | true |
| Glaze | 1676.7 | 0.0635882 | 584.262ms | 9378 | 4890 | 56256.4 | 5334.03 | 0.0343102 | 1.80569 | 3(Loss) | true |
| simdjson (ondemand) | 1260.63 | 0.109789 | 762.934ms | 9378 | 1280 | 77655.8 | 7094.53 | 0.0220192 | 2.40417 | 4(Loss) | true |
