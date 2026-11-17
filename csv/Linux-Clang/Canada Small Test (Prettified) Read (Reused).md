
----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2246.78 | 0.19527 | 616.642ms | 11579 | 2560 | 235793 | 4914.85 | 0.586367 | 1.09589 | 1(Win) | true |
| Jsonifier | 2005.98 | 0.0377307 | 688.25ms | 11579 | 40 | 172.558 | 5504.82 | 0.0410415 | 1.22819 | 2(Loss) | true |
| simdjson (ondemand) | 1928.34 | 0.12544 | 685.286ms | 11579 | 40 | 2064 | 5726.48 | 0.252829 | 1.27787 | 3(Loss) | true |
| Glaze | 1821.28 | 0.0617087 | 713.731ms | 11579 | 30 | 419.955 | 6063.1 | 0.082947 | 1.35354 | 4(Loss) | true |
