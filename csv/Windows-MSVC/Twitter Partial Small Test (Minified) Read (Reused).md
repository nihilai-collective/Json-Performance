
----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 5446.4 | 0.17863 | 56.5468ms | 2889 | 4890 | 3992.95 | 505.869 | 0.236889 | 0.538032 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 5440.62 | 0.271183 | 54.9496ms | 2889 | 1280 | 2413.97 | 506.406 | 0.613309 | 0.537774 | 1(Tie) | true |
| simdjson (ondemand) | 4360.3 | 0.412907 | 66.5843ms | 2889 | 320 | 2178.29 | 631.875 | 0.492126 | 0.678152 | 3(Loss) | true |
| Glaze | 3037.21 | 0.142343 | 92.2344ms | 2889 | 4890 | 8153.18 | 907.137 | 0.0313923 | 0.970728 | 4(Loss) | true |
