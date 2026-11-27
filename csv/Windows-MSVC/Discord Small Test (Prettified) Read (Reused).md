
----
### Discord Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1886.52 | 0.188712 | 389.799ms | 6701 | 40 | 1634.62 | 3387.5 | 0.0737463 | 1.30173 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1607.56 | 0.742447 | 445.104ms | 6701 | 640 | 557512 | 3975.31 | 0.260088 | 1.52917 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1601.65 | 0.0948024 | 454.507ms | 6701 | 160 | 2289.31 | 3990 | 0.25 | 1.53445 | 2(Tie) | true |
| simdjson (ondemand) | 1196.75 | 0.439139 | 571.589ms | 6701 | 1280 | 703855 | 5339.92 | 0.607907 | 2.0579 | 4(Loss) | true |
