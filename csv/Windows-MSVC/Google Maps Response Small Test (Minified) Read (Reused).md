
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1101.02 | 0.175849 | 435.42ms | 4390 | 40 | 1788.46 | 3802.5 | 0.0219106 | 2.2319 | 1(Win) | true |
| Glaze | 959.592 | 0.26638 | 490.067ms | 4390 | 2560 | 345780 | 4362.93 | 0.42703 | 2.5624 | 2(Loss) | true |
| Jsonifier | 741.872 | 0.163057 | 385.882ms | 4390 | 30 | 2540.23 | 5643.33 | 0.296209 | 3.31464 | 3(Loss) | true |
| simdjson (ondemand) | 574.43 | 0.165756 | 829.105ms | 4390 | 4890 | 713676 | 7288.32 | 1.06209 | 4.29341 | 4(Loss) | true |
