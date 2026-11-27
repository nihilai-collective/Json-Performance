
----
### Random Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10802.2 | 0.25328 | 49.5937ms | 5094 | 2560 | 3321.54 | 449.727 | 0.165304 | 0.215087 | 1(Win) | true |
| Glaze | 3079.57 | 0.496805 | 161.81ms | 5094 | 1280 | 78617.7 | 1577.5 | 0.0693825 | 0.790041 | 2(Loss) | true |
