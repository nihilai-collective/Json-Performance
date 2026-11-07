
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 2351.3 | 0.269296 | 437.723ms | 9378 | 2560 | 268599 | 3803.67 | 0.03904 | 1.04557 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 2342.01 | 0.0843173 | 446.356ms | 9378 | 160 | 1658.81 | 3818.75 | 0.262553 | 1.04977 | 1(Tie) | true |
| Glaze | 1703.94 | 0.105478 | 577.929ms | 9378 | 160 | 4904.09 | 5248.75 | 0.0476531 | 1.4444 | 3(Loss) | true |
| simdjson (ondemand) | 1215.09 | 0.19787 | 788.423ms | 9378 | 2560 | 543010 | 7360.43 | 0.115031 | 2.03039 | 4(Loss) | true |
