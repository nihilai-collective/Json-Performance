
----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 612.797 | 0.0512878 | 848.732ms | 4630 | 4890 | 66783 | 7205.5 | 0.0206905 | 4.94575 | 1(Win) | true |
| Jsonifier (two-stage) | 604.693 | 0.0752241 | 857.675ms | 4630 | 2560 | 77240.7 | 7302.07 | 0.123727 | 5.01151 | 2(Loss) | true |
| simdjson (ondemand) | 343.979 | 0.101715 | 1423.03ms | 4630 | 320 | 54552.4 | 12836.6 | 0.0170441 | 8.82161 | 3(Loss) | true |
| Glaze | 338.578 | 0.0839572 | 1427.9ms | 4630 | 1280 | 153451 | 13041.3 | 0.0197728 | 8.96163 | 4(Loss) | true |
