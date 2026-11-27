
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 8235.95 | 0.187117 | 7615.49ms | 631514 | 160 | 2.99563e+06 | 73125.6 | 0.725462 | 0.368924 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 8228.14 | 0.134786 | 7540.32ms | 631514 | 320 | 3.11458e+06 | 73195 | 0.0495007 | 0.369266 | 1(Tie) | true |
| simdjson (ondemand) | 5320.2 | 0.342018 | 5813.68ms | 631514 | 2560 | 3.8375e+08 | 113202 | 0.193647 | 0.571143 | 3(Loss) | true |
| Glaze | 3750.46 | 0.277835 | 8444.13ms | 631514 | 80 | 1.59242e+07 | 160582 | 0.147681 | 0.810255 | 4(Loss) | true |
