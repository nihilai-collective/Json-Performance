
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 2156.54 | 0.508785 | 179.66ms | 3370 | 4890 | 281141 | 1490.3 | 0.214978 | 1(Tie) | true |
| Glaze STATISTICAL TIE | 2127.25 | 0.505315 | 181.92ms | 3370 | 4890 | 285008 | 1510.82 | 0.0384535 | 1(Tie) | true |
| Jsonifier (two-stage) | 2073.01 | 0.502757 | 185.855ms | 3370 | 4890 | 297086 | 1550.34 | 0.222663 | 3(Loss) | true |
| simdjson (reflection) | 1723.08 | 0.384701 | 217.831ms | 3370 | 2560 | 131807 | 1865.2 | 0.723866 | 4(Loss) | true |
| simdjson (ondemand) | 1334.23 | 0.756087 | 277.06ms | 3370 | 2560 | 849150 | 2408.8 | 0.429894 | 5(Loss) | true |
