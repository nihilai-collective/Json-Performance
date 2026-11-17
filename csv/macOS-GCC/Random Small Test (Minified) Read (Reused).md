
----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1304.83 | 0.281239 | 491.753ms | 5094 | 4890 | 536129 | 3723.1 | 0.013393 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1289.9 | 0.527853 | 456.905ms | 5094 | 1280 | 505874 | 3766.2 | 0.0903582 | 1(Tie) | true |
| Glaze | 1084.62 | 0.351052 | 562.713ms | 5094 | 1280 | 316457 | 4479 | 0.271642 | 3(Loss) | true |
| simdjson (reflection) | 1033.22 | 0.343899 | 572.082ms | 5094 | 1280 | 334657 | 4701.8 | 0.0553286 | 4(Loss) | true |
| simdjson (ondemand) | 775.979 | 0.368013 | 741.598ms | 5094 | 2560 | 1.35889e+06 | 6260.5 | 0.481656 | 5(Loss) | true |
