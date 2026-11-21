
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 2355.63 | 0.199008 | 427.574ms | 9378 | 30 | 1712.64 | 3796.67 | 0.0877193 | 1.04584 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 2349.45 | 0.121683 | 457.028ms | 9378 | 30 | 643.678 | 3806.67 | 0.0876424 | 1.04658 | 1(Tie) | true |
| Glaze | 1577.4 | 0.175091 | 629.487ms | 9378 | 4890 | 481916 | 5669.8 | 0.132954 | 1.56187 | 3(Loss) | true |
| simdjson (ondemand) | 1434.03 | 0.330516 | 719.915ms | 9378 | 30 | 12747.1 | 6236.67 | 0.483351 | 1.71704 | 4(Loss) | true |
