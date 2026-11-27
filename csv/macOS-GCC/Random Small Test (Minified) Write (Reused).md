
----
### Random Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11020.9 | 4.47903 | 47.9101ms | 5094 | 640 | 249477 | 440.8 | 1.9573 | 1(Win) | true |
| simdjson (reflection) | 7640.79 | 2.13191 | 60.5599ms | 5094 | 1280 | 235174 | 635.8 | 2.28443 | 2(Loss) | true |
| Glaze | 2151.85 | 2.60417 | 236.072ms | 5094 | 160 | 553035 | 2257.6 | 0.355619 | 3(Loss) | true |
