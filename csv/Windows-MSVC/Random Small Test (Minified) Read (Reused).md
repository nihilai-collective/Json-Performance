
----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 937.194 | 0.169067 | 647.755ms | 5094 | 4890 | 375568 | 5183.58 | 0.100415 | 2.62826 | 1(Win) | true |
| Jsonifier (two-stage) | 850.873 | 0.227603 | 688.784ms | 5094 | 1280 | 216150 | 5709.45 | 1.01181 | 2.89639 | 2(Loss) | true |
| Glaze | 830.43 | 0.149924 | 711.839ms | 5094 | 40 | 3076.92 | 5850 | 0.0569476 | 2.97003 | 3(Loss) | true |
| simdjson (ondemand) | 608.896 | 0.182654 | 930.205ms | 5094 | 2560 | 543664 | 7978.4 | 0.110282 | 4.05293 | 4(Loss) | true |
